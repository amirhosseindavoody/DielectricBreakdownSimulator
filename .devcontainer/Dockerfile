# You can pick any Debian/Ubuntu-based image. 😊
FROM mcr.microsoft.com/vscode/devcontainers/base:0-bullseye

# Options for setup script
ARG INSTALL_ZSH="true"
ARG UPGRADE_PACKAGES="false"
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID
# Install needed packages and setup non-root user. Use a separate RUN statement to add your own dependencies.
COPY library-scripts/*.sh /tmp/library-scripts/
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && /bin/bash /tmp/library-scripts/common-debian.sh "${INSTALL_ZSH}" "${USERNAME}" "${USER_UID}" "${USER_GID}" "${UPGRADE_PACKAGES}" "true" "true" \
    && apt-get install -y pkg-config zip g++ zlib1g-dev unzip python \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* /tmp/library-scripts

# Install Bazel
ARG BAZELISK_VERSION=latest
ARG BAZELISK_DOWNLOAD_SHA=dev-mode
RUN ([ "${BAZELISK_VERSION}" = "latest" ] \
    && ( echo "BAZELISK_VERSION is latest" && curl -fSsL -o /usr/local/bin/bazelisk https://github.com/bazelbuild/bazelisk/releases/${BAZELISK_VERSION}/download/bazelisk-linux-amd64 ) \
    || (echo "BAZELISK_VERSION is: ${BAZELISK_VERSION}" && curl -fSsL -o /usr/local/bin/bazelisk https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_VERSION}/bazelisk-linux-amd64) ) \
    && ([ "${BAZELISK_DOWNLOAD_SHA}" = "dev-mode" ] || echo "${BAZELISK_DOWNLOAD_SHA} */usr/local/bin/bazelisk" | sha256sum --check - ) \
    && chmod 0755 /usr/local/bin/bazelisk

ARG BUILDTOOLS_VERSION=latest
ARG BUILDTOOLS_DOWNLOAD_SHA=dev-mode
RUN ([ "${BUILDTOOLS_VERSION}" = "latest" ] \
    && ( echo "BUILDTOOLS_VERSION is latest" && curl -fSsL -o /usr/local/bin/buildtools https://github.com/bazelbuild/buildtools/releases/${BUILDTOOLS_VERSION}/download/buildifier-linux-amd64 ) \
    || (echo "BUILDTOOLS_VERSION is: ${BUILDTOOLS_VERSION}" && curl -fSsL -o /usr/local/bin/buildtools https://github.com/bazelbuild/buildtools/releases/download/${BUILDTOOLS_VERSION}/buildifier-linux-amd64) ) \
    && ([ "${BUILDTOOLS_DOWNLOAD_SHA}" = "dev-mode" ] || echo "${BUILDTOOLS_DOWNLOAD_SHA} */usr/local/bin/buildtools" | sha256sum --check - ) \
    && chmod 0755 /usr/local/bin/buildtools

# [Optional] Uncomment this section to install additional OS packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

# Install oy-my-zsh
RUN git clone https://github.com/zsh-users/zsh-autosuggestions /home/vscode/.oh-my-zsh/custom/plugins/zsh-autosuggestions
COPY .zshrc /home/vscode/.zshrc
RUN chown -R vscode:vscode /home/vscode/.zshrc