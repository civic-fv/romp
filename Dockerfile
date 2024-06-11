
FROM ubuntu:22.04

MAINTAINER Andrew Osterhout andrew.osterhout@utah.edu

ARG modelDir=../romp-models

ENV TZ=America/Denver
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && \
    apt -y upgrade && \
    apt -y install \
        build-essential \
        cmake \
        clang \
        git \
        ssh \
        bison \
        flex \
        libgmp-dev \
        python3 \
        python3-pip \
        wget \
        zsh \
        bat \
        rumur
RUN python3 -m pip install multiset

RUN useradd -ms $(which zsh) romp

# ========================================== Build Romp ========================================== #
RUN mkdir -p /home/romp/romp ; chown romp:romp /home/romp/romp
COPY --chown=romp:romp --chmod=r-xr-xr-x ./romp /home/romp/romp/romp
COPY --chown=romp:romp --chmod=r-xr-xr-x ./libmurphi /home/romp/romp/libmurphi
COPY --chown=romp:romp --chmod=r-xr-xr-x ./misc /home/romp/romp/misc
COPY --chown=romp:romp --chmod=r-xr-xr-x ./common /home/romp/romp/common
COPY --chown=romp:romp --chmod=r-xr-xr-x ./CMakeLists.txt /home/romp/romp
# DBG: see if propper files got added
# RUN ls -lah /home/romp/romp && sleep 10
ENV MURPHI_VERSION="romp-v0.0.2"
RUN chmod +x /home/romp/romp/misc/xxd.py ; \
    chmod +x /home/romp/romp/libmurphi/src/make-version.py ; \
    mkdir -p /tmp/romp && \
    cd /tmp/romp && \
    cmake /home/romp/romp -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -B/tmp/romp -G "Unix Makefiles" && \
    cd /tmp/romp/romp && \
    make && \
    make install && \
    cd /home/romp && \
    rm -rf /tmp/romp


# ========================================= Build Cmurphi ======================================== #
# download and install known good CMurphi
RUN mkdir -p /tmp/cmurphi && \
    wget http://mclab.di.uniroma1.it/site/softwareopensource/cmurphi5.5.0.tgz -O /tmp/cmurphi5.5.0.tgz && \
    tar -xzvf /tmp/cmurphi5.5.0.tgz -C /tmp && \
    rm -f /tmp/cmurphi5.5.0.tgz && \
    cd /tmp/cmurphi5.5.0/src && \
    make
# manually install
RUN cp /tmp/cmurphi5.5.0/src/mu /usr/bin/mu && \
    mkdir -p /usr/lib/cmurphi/include && \
    cp -rf /tmp/cmurphi5.5.0/include /usr/lib/cmurphi/include
# manually clean up
RUN rm -rf /tmp/cmurphi && \
    rm -f /home/romp/.wget-hsts

# ============================================ Set Env =========================================== #

RUN mkdir -p /home/romp/models
RUN chown -R romp:romp /home/romp/models && \
    chmod -R 775 /home/romp/models
COPY --chown=romp:romp --chmod=rwxrwxr-x ./tests/*.m /home/romp/models
COPY --chown=romp:romp --chmod=r-xr-xr-x ./tests/README.md /home/romp/models
# COPY --chown=romp:romp --chmod=r-xr-xr-x ./tests/makefile /home/romp/models
# RUN echo -e "\nROMP := /usr/bin/romp\n" >> /home/romp/models/makefile && \
#     echo -e "\nRUMUR := /usr/bin/rumur\n" >> /home/romp/models/makefile && \
#     echo -e "\nCMURPHI := /usr/bin/mu\n" >> /home/romp/models/makefile && \
#     echo -e "\nCMURPHI_INCLUDE_DIR := /usr/lib/cmurphi/include\n" >> /home/romp/models/makefile
COPY --chown=romp:romp --chmod=r-xr-xr-x ./Dockerfiles/makefile /home/romp/models

ENV SHELL=/usr/bin/zsh
# RUN mv /bin/sh /bin/_sh && \
#     ln -s /bin/zsh /bin/sh && \
#     mv /usr/bin/sh /usr/bin/_sh && \
#     ln -s /usr/bin/zsh /usr/bin/sh

# Default powerline10k theme, no plugins installed
# RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.5/zsh-in-docker.sh)"
RUN git clone --depth=1 https://github.com/romkatv/powerlevel10k.git /home/romp/.powerlevel10k && \
    echo "source /home/romp/.powerlevel10k/powerlevel10k.zsh-theme" >> /home/romp/.zshrc && \
    cd /home/romp/.powerlevel10k && \
    exec zsh
COPY --chown=romp:romp --chmod=rwxr-xr-x ./Dockerfiles/.zshrc /home/romp
COPY --chown=romp:romp --chmod=rwxr-xr-x ./Dockerfiles/.p10k.zsh /home/romp

# RUN echo "alias make='make ROMP=romp RUMUR=rumur CMURPHI=mu CMURPHI_INCLUDE_DIR=/usr/lib/cmurphi/include'" >> /home/romp/.bashrc
# RUN echo "alias make='make ROMP=romp RUMUR=rumur CMURPHI=mu CMURPHI_INCLUDE_DIR=/usr/lib/cmurphi/include'" >> /home/romp/.zshrc

# DBG: make sure all model checkers are on path
# RUN eval echo eval "$(which romp)  --  $(which rumur)  --  $(which mu)  --  $(which make) " && sleep 10

# CMD [ "source /home/romp/.zshrc", "zsh"]
# CMD [ "zsh" ]

# ======================================== Last Min Copys ======================================== #
# for more optimal docker build caching put these at the end

COPY --chown=romp:romp --chmod=r-xr-xr-x ./doc /home/romp/romp/doc
COPY --chown=romp:romp --chmod=r-xr-xr-x ./.vscode /home/romp/romp/.vscode
COPY --chown=romp:romp --chmod=r-xr-xr-x ./.gitignore /home/romp/romp
COPY --chown=romp:romp --chmod=r-xr-xr-x ./.clang-format /home/romp/romp
COPY --chown=romp:romp --chmod=r-xr-xr-x ./README.rst /home/romp/romp
COPY --chown=romp:romp --chmod=r-xr-xr-x ./LICENSE /home/romp/romp
COPY --chown=romp:romp --chmod=rwxrwxr-x ./tests/*.md /home/romp/romp/tests
COPY --chown=romp:romp --chmod=rwxrwxr-x ./.git /home/romp/romp/.git

COPY --chown=romp:romp --chmod=rwxrwxr-x ./tests/*.py /home/romp/romp/tests
COPY --chown=romp:romp --chmod=rwxrwxr-x ./tests/makefile /home/romp/romp/tests
COPY --chown=romp:romp --chmod=rwxrwxr-x ./tests/*.m /home/romp/romp/tests


USER romp
WORKDIR /home/romp/models
CMD [ "/bin/sh", "-c", "/usr/bin/zsh" ]
