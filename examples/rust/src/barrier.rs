#[cfg(test)]
mod tests {
    use std::sync::{Arc, Barrier};
    use std::thread;

    #[test]
    fn test_barrier_thread_synchronisation() {
        const NUM_THREADS: usize = 10;
        let mut thread_handles = Vec::with_capacity(NUM_THREADS);

        // create shared barrier across NUM_THREADS
        let barrier = Arc::new(Barrier::new(NUM_THREADS));

        for _ in 0..NUM_THREADS {
            let thread_barrier = Arc::clone(&barrier);

            // the same messages will be printed together.
            // you will NOT see any interleaving.
            let thread_handle = thread::spawn(move || {
                println!("before wait");
                thread_barrier.wait();
                println!("after wait");
            });
            thread_handles.push(thread_handle)
        }

        // gracefully wait for threads to finish.
        for handle in thread_handles {
            handle.join().unwrap();
        }
    }
}
