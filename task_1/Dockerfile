FROM gcc:latest

COPY . /usr/src/multiprocessing-programming

WORKDIR /usr/src/multiprocessing-programming

RUN g++ -o Test runge–kutta-method.cpp

CMD [ "./Test" ]