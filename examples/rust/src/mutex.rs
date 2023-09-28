// struct SinglyLinkedList {
//     value: i32,
//     child: Mutex<Arc<SinglyLinkedList>>,
// }

// fn delete(root: Mutex<SinglyLinkedList>, value: i32) -> {

// }

#[cfg(test)]
mod tests {
    use std::sync::{Arc, Mutex};
    use std::thread;

    #[test]
    fn test_mutex_count_across_threads() {
        let counter_start = 0;
        let num_threads = 5;

        // create a shared Mutex for the counter
        let counter = Arc::new(Mutex::new(counter_start));

        let mut thread_handles = vec![];

        for i in 0..num_threads {
            let counter = Arc::clone(&counter);

            // Spawn a thread that increments the counter
            let thread_handle = thread::spawn(move || {
                // entering "critical section"
                let mut counter = counter.lock().expect("unable to acquire mutex");

                // simulate some work
                thread::sleep(std::time::Duration::from_millis(i));

                // Increment the counter
                *counter += 1;
                println!("Thread {} incremented the counter to {}", i, *counter);
            });

            thread_handles.push(thread_handle);
        }

        // wait for all threads to finish
        for handle in thread_handles {
            handle.join().unwrap();
        }

        // access the final counter value
        let final_counter = *counter.lock().expect("unable to acquire mutex");
        println!("Final counter value: {}", final_counter);

        // test assertion
        assert_eq!(final_counter, counter_start + num_threads)
    }
}
