FROM ubuntu:latest
ENV DEBIAN_FRONTEND=noninteractive
WORKDIR /opt
VOLUME /opt
RUN apt update && \
    apt install -y valgrind clang wget vim && \
    apt install -y python3 python3-pip python3-venv && \
    apt install -y build-essential cmake git curl && \
    apt install -y libreadline-dev && \
    apt install -y sudo
RUN apt update && \
    wget https://raw.github.com/xicodomingues/francinette/master/bin/install.sh && sed -i 's|"\$HOME"|/opt|g' install.sh && sed -i 's|RC_FILE="\$HOME/.zshrc"|RC_FILE="/root/.bashrc"|g' install.sh && chmod +x install.sh && ./install.sh
RUN /opt/francinette/tester.sh -u
RUN python3 -m pip install --upgrade pip && python3 -m pip install norminette
ENV HOME /home/root
CMD ["bash"]
