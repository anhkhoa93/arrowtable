FROM arrow-env:latest

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /arrowtable
WORKDIR /arrowtable
RUN cd /arrowtable && cmake ./
RUN make

RUN cd /arrowtable/tests && cmake ./ && make && make install
#RUN cd /arrowtable/tests && ./arrow-table-test

# This command runs your application, comment out this line to compile only
CMD ["/arrowtable/run.sh"]

LABEL Name=arrowtable Version=1.0.0
