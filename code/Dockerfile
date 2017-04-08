FROM ubuntu:latest

RUN apt-get update && apt-get install -y git libboost-all-dev 
RUN git clone https://github.com/cloudy/Number-Theory-PKC-Project.git /opt/nt
WORKDIR /home
RUN make 
EXPOSE 12345

ENTRYPOINT ["python3", "/opt/nt/app.py"]