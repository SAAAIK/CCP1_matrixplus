FROM srzzumix/googletest:latest

COPY ./ /code/

RUN apt update && apt install -y valgrind 

WORKDIR /code/
ENTRYPOINT ["make", "vg"]