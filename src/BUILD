cc_library(
    name = "constants",
    hdrs = ["constants.h"],
    deps = [
    ],
)

cc_library(
    name = "node",
    srcs = ["node.cc"],
    hdrs = ["node.h"],
    deps = [":constants"],
)

cc_library(
    name = "node_manager",
    srcs = ["node_manager.cc"],
    hdrs = ["node_manager.h"],
    deps = [
        ":constants",
        ":node",
        ":random_position_generator",
        "@com_google_absl//absl/log",
    ],
)

cc_library(
    name = "random_position_generator",
    srcs = ["random_position_generator.cc"],
    hdrs = ["random_position_generator.h"],
    deps = [
        ":constants",
        ":node",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/log:check",
    ],
)

cc_test(
    name = "random_position_generator_test",
    size = "small",
    srcs = ["random_position_generator.cc"],
    deps = [
        ":random_position_generator",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "breakdown_simulator",
    srcs = ["breakdown_simulator.cc"],
    hdrs = ["breakdown_simulator.h"],
    deps = [
        ":constants",
        ":node",
        ":node_manager",
        ":random_position_generator",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":breakdown_simulator",
        ":constants",
        ":node",
        ":random_position_generator",
        "@com_github_gflags_gflags//:gflags",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/time",
    ],
)
