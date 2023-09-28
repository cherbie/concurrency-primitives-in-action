#[cfg(test)]
mod tests {
    use std::sync::{Arc, RwLock, RwLockReadGuard, RwLockWriteGuard};
    use std::thread;

    /// `std::sync::RwLock` to demonstrate multiple readers and single writer
    #[test]
    fn test_rwlock_example() {
        // create shared data protected by a RwLock
        let data = Arc::new(RwLock::new(0));

        // clone data for the readers and writer
        let data_reader1 = Arc::clone(&data);
        let data_reader2 = Arc::clone(&data);
        let data_writer = Arc::clone(&data);

        // spawn reader threads
        let reader1 = thread::spawn(move || {
            let read_lock: RwLockReadGuard<'_, i32> = data_reader1.read().unwrap();
            println!("Reader 1: Value = {}", *read_lock);
        });

        let reader2 = thread::spawn(move || {
            // multiple readers can acquire the value
            let read_lock = data_reader2.read().unwrap();
            println!("Reader 2: Value = {}", *read_lock);

            // simulate some work
            // ... writer cannot acquire lock until all readers are dropped
            // thread::sleep(std::time::Duration::from_secs(10));
        });

        // spawn a writer thread
        let writer = thread::spawn(move || {
            let mut write_lock: RwLockWriteGuard<'_, i32> = data_writer.write().unwrap();
            *write_lock += 42;
            println!("Writer: Value updated to {}", *write_lock);
        });

        // wait for all threads to finish
        reader1.join().unwrap();
        reader2.join().unwrap();
        writer.join().unwrap();
    }
}
