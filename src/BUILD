cc_library(
    name = "constants",
    hdrs = ["constants.h"],
    deps = [
    ]
)

cc_library(
    name = "node",
    hdrs = ["node.h"],
    srcs = ["node.cc"],
    deps = [":constants"]
)

cc_library(
    name = "random_position_generator",
    hdrs = ["random_position_generator.h"],
    srcs = ["random_position_generator.cc"],
    deps = [
        ":constants",
        ":node",
        "@com_google_absl//absl/hash",
        "@com_github_google_glog//:glog",
    ]
)

cc_library(
    name = "breakdown_simulator",
    hdrs = ["breakdown_simulator.h"],
    srcs = ["breakdown_simulator.cc"],
    deps = [
        ":node",
        ":constants",
        ":random_position_generator",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/strings",
        "@com_github_google_glog//:glog",
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps=[
        ":node",
        ":constants",
        ":random_position_generator",
        ":breakdown_simulator",
        "@com_google_absl//absl/hash",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
)