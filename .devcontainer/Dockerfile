# Two stages from one file:
#   ci   CLI and data viewer toolchain. GitHub Actions runs the ultrazohm_cli and
#        ultrazohm_dataviewer tasks in this stage (see .github/workflows/ci-image.yml).
#   dev  The development container: the ci stage plus firmware, docs and Java tools.
# Developers and CI therefore build and test with the same toolchain.

FROM node:22.23.5-bookworm-slim@sha256:be979e5523c76fa4d5ca4ebd3099078f220aa47ec39c48ad5b5df9314debd6eb AS node_tools

# Debian trixie-based Python image.
FROM docker.io/library/python:3.12-trixie@sha256:5411fa1b302c43f510324381162b5f5d0d93b9ee2af538f09d944f0d290ee3cb AS ci

COPY --from=node_tools /usr/local/bin/node /usr/local/bin/node
COPY --from=node_tools /usr/local/lib/node_modules /usr/local/lib/node_modules
RUN ln -s ../lib/node_modules/npm/bin/npm-cli.js /usr/local/bin/npm \
 && ln -s ../lib/node_modules/npm/bin/npx-cli.js /usr/local/bin/npx

# Build tools and GUI runtime libraries for headless ImGui tests.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends build-essential gdb gdbserver tcl zstd xvfb xauth libgtk-3-0 libnss3 libasound2t64 libgbm1 libxss1 libatk-bridge2.0-0 \
                                                  make \
                                                  git \
                                                  curl \
                                                  ca-certificates \
                                                  pkg-config \
                                                  libssl-dev \
                                                  xvfb \
                                                  xauth \
                                                  libgl1-mesa-dri \
                                                  libgl1 \
                                                  libx11-6 \
                                                  libxext6 \
                                                  libxau6 \
                                                  libxdmcp6 \
                                                  libxcb1 \
     && rm -rf /var/lib/apt/lists/*

# Rust CLI and native Python package. Pin the same toolchain as ultrazohm_cli.
ENV RUSTUP_HOME=/opt/rustup CARGO_HOME=/opt/cargo
ENV PATH="/opt/cargo/bin:$PATH"
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs -o /tmp/rustup.sh \
    && sh /tmp/rustup.sh -y --profile minimal --default-toolchain 1.90.0 --no-modify-path \
    && rustup component add rustfmt clippy \
    && rm /tmp/rustup.sh
# ziglang lets maturin link portable manylinux_2_28 wheels without a Docker build.
COPY build-tools.txt /tmp/uz-build-tools.txt
RUN pip install --no-cache-dir -r /tmp/uz-build-tools.txt


FROM ci AS dev

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends cmake \
                                                  gdb \
                                                  ruby \
                                                  texlive \
                                                  texlive-lang-german \
                                                  texlive-latex-extra \
                                                  texlive-pictures \
                                                  texlive-science \
                                                  texlive-luatex \
                                                  texlive-plain-generic \
                                                  pdf2svg \
                                                  ghostscript \
                                                  git-lfs \
                                                  doxygen \
                                                  openjdk-21-jdk \
                                                  ant

# Ruby 3.3's RDoc parser currently fails while generating Ceedling's docs.
RUN gem install --no-document ceedling && ln -sf /usr/local/bin/ceedling /usr/bin/ceedling

RUN wget -O pcre-8.45.tar.gz https://github.com/pfultz2/pcre/archive/refs/tags/8.45.tar.gz \
     && echo "d6f7182602a775a7d500a0cedca6449af0400c6493951513046d17615ed0bf11  pcre-8.45.tar.gz" | sha256sum -c - \
     && tar -xzf pcre-8.45.tar.gz \
     && cd pcre-8.45 \
     && ./configure \
     && make -j"$(nproc)" \
     && make install \
     && ldconfig \
     && cd / \
     && rm -rf /pcre-8.45 /pcre-8.45.tar.gz

RUN wget https://github.com/danmar/cppcheck/archive/refs/tags/2.20.0.tar.gz \
     && tar -xzf 2.20.0.tar.gz \
     && cmake -S cppcheck-2.20.0 -B cppcheck-2.20.0/build \
          -DCMAKE_BUILD_TYPE=Release \
          -DUSE_MATCHCOMPILER=On \
          -DHAVE_RULES=On \
          -DFILESDIR=/usr/share/cppcheck \
     && cmake --build cppcheck-2.20.0/build -j"$(nproc)" \
     && cmake --install cppcheck-2.20.0/build \
     && ln -sf /usr/local/bin/cppcheck /usr/bin/cppcheck \
     && rm -rf 2.20.0.tar.gz cppcheck-2.20.0

# Set env variables for gitpod, see https://github.com/gitpod-io/gitpod/issues/7110
ENV PYTHONUSERBASE=/workspace/.pip-modules
ENV PATH=$PYTHONUSERBASE/bin:$PATH
ENV PIP_USER=yes

ENV JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
ENV PATH="$JAVA_HOME/bin:$PATH"

ENV UZ_DEVELOPMENT_ENVIRONMENT=/opt/ultrazohm/development
ENV PATH="/opt/ultrazohm/development/bin:$PATH"
