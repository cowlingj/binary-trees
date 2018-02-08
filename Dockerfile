FROM gcc:4.9
WORKDIR /tree
ADD . /tree
RUN make simple
CMD ["/tree/bin/simple"]