FROM ubuntu:22.04

# Update the system and install build dependencies (including readline)
RUN apt-get update && apt-get install -y \
	build-essential \
	clang \
	make \
	libreadline-dev \
	&& rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy all project files into the container
COPY . .

# Compile the project using the Makefile
RUN make

# Command to run minishell on container startup
CMD ["./minishell"]