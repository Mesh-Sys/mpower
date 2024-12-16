pkgname=mpower
pkgver=1.0
pkgrel=1
pkgdesc="A POWER MANAGER FOR LINUX"
arch=('x86_64')
license=('custom')
depends=('gcc' 'gcc-libs')
conflicts=('power-profiles-daemon')
source=("mpower_${pkgver}_x64.tar.gz")
sha256sums=('SKIP')

build() {
	gcc -O2 -DNDEBUG -Wall "$srcdir"/mpower_${pkgver}_x64/$pkgname.c -o "$srcdir"/mpower_${pkgver}_x64/$pkgname
}

package() {
	install -d "$pkgdir"/usr/bin
	install -d "$pkgdir"/etc
	install -d "$pkgdir"/usr/lib/systemd/system

	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname "$pkgdir"/usr/bin/$pkgname
	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname.conf "$pkgdir"/etc/$pkgname.conf
	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname.service "$pkgdir"/usr/lib/systemd/system/$pkgname.service
}