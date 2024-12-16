pkgname=mpower
pkgver=1.0
pkgrel=1
pkgdesc="A POWER MANAGER BY SkyNotion"
arch=('x86_64')
license=('custom')
depends=('gcc' 'gcc-libs')
conflicts=('power-profiles-daemon')
source=("mpower_${pkgver}_x64.tar.gz")
sha256sums=('none')

build() {

	g++ -O3 -DNDEBUG -Wall "$srcdir"/mpower_${pkgver}_x64/$pkgname.cpp -o "$srcdir"/mpower_${pkgver}_x64/$pkgname

}

package() {

	msg2 "creating directory structure********"

	install -d "$pkgdir"/usr/bin
	install -d "$pkgdir"/etc
	install -d "$pkgdir"/usr/lib/systemd/system

	msg2 "coping files*******"

	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname "$pkgdir"/usr/bin/$pkgname
	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname.json "$pkgdir"/etc/$pkgname.json
	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname.service "$pkgdir"/usr/lib/systemd/system/$pkgname.service

	msg2 "done coping files********"

}