# Maintainer: SlurpyIsADev <ThisisA1029@gmail.com>
pkgname='tty-timed'
pkgver=1.0.0
pkgrel=1
pkgdesc="A simple TUI timer and stopwatch script"
arch=('any')
url="https://github.com/SlurpyIsADev/TTY-Timed"
license=('MIT')
depends=('ncurses' 'glibc')
makedepends=('git' 'gcc')
source=('tty-timed::git+https://github.com/SlurpyIsADev/TTY-Timed')
sha256sums=('SKIP')

# Please refer to the 'USING VCS SOURCES' section of the PKGBUILD man page for
# a description of each element in the source array.

pkgver() {
	cd "$srcdir/${pkgname%-VCS}"

# The examples below are not absolute and need to be adapted to each repo. The
# primary goal is to generate version numbers that will increase according to
# pacman's version comparisons with later commits to the repo. The format
# VERSION='VER_NUM.rREV_NUM.HASH', or a relevant subset in case VER_NUM or HASH
# are not available, is recommended.

# Bazaar
	# printf "r%s" "$(bzr revno)"

# Git, tags available
	# printf "%s" "$(git describe --long | sed 's/\([^-]*-\)g/r\1/;s/-/./g')"

# Git, no tags available
	printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
	cd $pkgname || cd TTY-Timed || cd TTY-Timed-main 
	gcc tty-timed.c Font/default-font.c -lncurses -o tty-timed -DCOMMIT="\"$(git rev-parse HEAD)\"" 
}

package() {
	cd $pkgname || cd TTY-Timed || cd TTY-Timed-main 	
	install -Dm755 ./tty-timed "$pkgdir/usr/bin/tty-timed"
	install -Dm644 ./README.md "$pkgdir/usr/share/doc/$pkgname"

}
