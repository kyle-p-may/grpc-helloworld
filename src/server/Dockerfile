FROM kylemay/ghw:tagname
COPY . /src
WORKDIR /src
RUN make
EXPOSE 50051
ENTRYPOINT make deploy