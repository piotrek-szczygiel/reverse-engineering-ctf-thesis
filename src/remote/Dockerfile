FROM ubuntu:groovy

RUN apt-get update \
    && apt-get install -y openssh-server \
    && useradd -ms /bin/bash ctf \
    && echo "ctf:agh-reverse-engineering" | chpasswd \
    && mkdir -p /var/run/sshd

COPY remote /home/ctf/remote
COPY flag.txt /home/ctf/flag.txt

RUN chmod 771 /home/ctf/remote \
    && chmod u+s /home/ctf/remote \
    && chmod 600 /home/ctf/flag.txt

EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]
