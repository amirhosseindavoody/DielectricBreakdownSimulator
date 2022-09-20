# Dielectric Breakdown Simulator

## Compile and run the code
The code is compilable using [`bazel`](https://bazel.build/).

The `.devcontainer` directory creates a docker container that installs [`bazelisk`](https://github.com/bazelbuild/bazelisk) which is a friendly launcher for Bazel. You can run the same build commands using `bazel` or `bazelisk`.

* Compile everythin:
    ```
    bazelisk build src/...
    ```

* [Hedron's Compile Commands Extractor for Bazel](https://github.com/hedronvision/bazel-compile-commands-extractor)
    ```
    bazel run @hedron_compile_commands//:refresh_all
    ```