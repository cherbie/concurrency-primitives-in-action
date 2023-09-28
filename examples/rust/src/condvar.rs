#[cfg(test)]
mod tests {
    use std::sync::{Arc, Condvar, Mutex};
    use std::thread;

    /// In Rust, you can use condition variables (CondVar) in combination with mutexes to
    /// create synchronization mechanisms for managing thread communication and synchronization.
    ///
    /// Here's an example of a Rust application using CondVar to coordinate two threads:s
    #[test]
    fn test_condvar_consumer_producer_channel() {
        // create shared data protected by a mutex
        let data = Arc::new((Mutex::new(false), Condvar::new()));

        // clone data for the producer and consumer
        let data_producer = Arc::clone(&data);
        let data_consumer = Arc::clone(&data);

        // spawn the producer thread
        let producer_thread_handle = thread::spawn(move || {
            let (lock, cvar) = &*data_producer;

            // lock the mutex
            let mut started = lock.lock().unwrap();

            // perform some work here
            println!("Producer: Starting some work...");

            // simulate work by sleeping
            thread::sleep(std::time::Duration::from_secs(2));

            // signal the consumer that work is done
            *started = true;
            cvar.notify_one();
        });

        // spawn the consumer thread
        let consumer_thread_handle = thread::spawn(move || {
            let (lock, cvar) = &*data_consumer;

            // lock the mutex
            let mut started = lock.lock().unwrap();

            // wait for the producer to finish work
            while !*started {
                started = cvar.wait(started).unwrap();
            }

            // continue with consumer's work
            println!("Consumer: Work completed!");
        });

        // wait for both threads to finish
        producer_thread_handle.join().unwrap();
        consumer_thread_handle.join().unwrap();
    }
}
