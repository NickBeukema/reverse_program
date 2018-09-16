FROM rsmmr/clang

# Update System Packages
RUN apt-get update
RUN apt-get -qq update
RUN apt-get install -y curl

# Install Node
# https://nodejs.org/en/download/package-manager/#debian-and-ubuntu-based-linux-distributions
RUN curl -sL https://deb.nodesource.com/setup_8.x | bash -
RUN apt-get install -y nodejs # npm

RUN update-alternatives --install /usr/bin/node node /usr/bin/nodejs 10

# Install Autocompile
RUN git clone https://github.com/NickBeukema/auto-compile-c-programs.git compiler


WORKDIR compiler
RUN npm install

COPY . app
COPY entry.sh .

WORKDIR app

CMD [ "sh", "entry.sh" ]
