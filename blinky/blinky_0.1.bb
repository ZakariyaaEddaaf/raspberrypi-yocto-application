SUMMARY = "blink led"
SECTION = "examples"
LICENSE = "CLOSED"

SRC_URI = "file://main.cpp \ 
            file://driver.cpp\
            file://driver.hpp\
            file://led.cpp\
            file://led.hpp"

S = "${WORKDIR}"

do_compile() {
	     ${CXX} ${CXXFLAGS} ${LDFLAGS} main.cpp driver.cpp led.cpp -o blinky 
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 blinky ${D}${bindir}
}

FILES_${PN} += "${bindir}/blinky_0.1"