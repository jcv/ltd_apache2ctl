# Set this variable to the name of the group that is allowed to restart apache.
webadmingroup = webadmin

all: ltd_apache2ctl

ltd_apache2ctl:
	gcc ltd_apache2ctl.c -o ltd_apache2ctl

install: ltd_apache2ctl
	install -m 6550 -g $(webadmingroup) -o root ltd_apache2ctl /usr/local/bin

.PHONY: install

clean:
	rm ltd_apache2ctl

