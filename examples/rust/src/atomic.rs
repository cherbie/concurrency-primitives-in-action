#[cfg(test)]
mod tests {
    use std::sync::{
        atomic::{AtomicUsize, Ordering},
        Arc,
    };
    use std::thread;

    #[test]
    fn test_atomic_count_across_threads() {
        const COUNTER_START: usize = 0;
        const NUM_THREADS: usize = 5;

        // create an atomic integer for the counter
        let counter = Arc::new(AtomicUsize::new(COUNTER_START));

        let mut thread_handles = vec![];
        for i in 0..NUM_THREADS {
            let counter = Arc::clone(&counter);

            // spawn a thread that increments the counter
            let thread_handle = thread::spawn(move || {
                // simulate some work
                thread::sleep(std::time::Duration::from_millis(i.try_into().unwrap()));

                // increment the counter atomically
                counter.fetch_add(1, Ordering::Relaxed);

                println!("Thread {} incremented the counter", i);
            });

            thread_handles.push(thread_handle);
        }

        // wait for all threads to finish
        for handle in thread_handles {
            handle.join().unwrap();
        }

        // access the final counter value
        let final_counter = counter.load(Ordering::Relaxed);
        println!("Final counter value: {}", final_counter);

        assert_eq!(final_counter, COUNTER_START + NUM_THREADS);
    }
}
