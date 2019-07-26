FROM gcc:4 AS builder
COPY . /usr/src/app
WORKDIR /usr/src/app
RUN make build

FROM alpine:3.6
WORKDIR /usr/src/app
RUN apk add --update ncurses-libs
COPY --from=builder /usr/src/app/bin .

ENV TERM=xterm-color
ENV LANG="en_US.UTF-8" \
    LC_ALL="en_US.UTF-8" \
    LANGUAGE="en_US.UTF-8"
CMD ["./minesweeper"]

