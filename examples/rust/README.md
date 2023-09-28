## Rust Concurrency Primitive Examples

### Cookbook

#### How to show stdout io when running `cargo test`?

```bash
cargo test -- --nocapture
```

#### How to disable tests running in parallel?

```bash
cargo test -- --test-threads 1
```