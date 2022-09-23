# Dielectric Breakdown Simulator

## Compiling the code
The code is compilable using [`bazel`](https://bazel.build/).

The `.devcontainer` directory creates a docker container that installs [`bazelisk`](https://github.com/bazelbuild/bazelisk) which is a friendly launcher for Bazel. You can run the same build commands using `bazel` or `bazelisk`.

* Compile everythin:
    ```
    bazelisk build src/...
    ```
## Better code completion and IDE 
* [Hedron's Compile Commands Extractor for Bazel](https://github.com/hedronvision/bazel-compile-commands-extractor): This build rule adds a `compile_commands.json` file and an `external` directory to the Bazel workspace directory so that the IDE works better with the dependency recovery.
    ```
    bazelisk run @hedron_compile_commands//:refresh_all
    ```

## Class definitions
* `Node` class represents a point in space that breakdown has happened.
* `NodeManager` class is responsible for creating new `nodes` as the simulation progresses.
    * This class depends on `Node` class and `RandomPositionGenerator` class.
* `RandomPositionGenerator` creates random positions for breakdown locations.
* `BreakdownDetector` is responsible to detect breakdowns