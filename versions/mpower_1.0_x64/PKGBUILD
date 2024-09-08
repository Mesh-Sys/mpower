pkgname=mpower
pkgver=1.0
pkgrel=1
pkgdesc="A POWER MANAGER BY SkyNotion"
arch=('x86_64')
license=('custom')
depends=('gcc' 'gcc-libs')
conflicts=('power-profiles-daemon')
source=("mpower_${pkgver}_x64.tar.gz")
sha256sums=('de66708e82b289c43d1cfd1a008307d9a06c1b76016a89ac4e0e7acfccf2885f')

build() {

	gcc -O2 -DNDEBUG -Wall "$srcdir"/mpower_${pkgver}_x64/$pkgname.c -o "$srcdir"/mpower_${pkgver}_x64/$pkgname

}

package() {

	msg2 "creating directory structure********"

	install -d "$pkgdir"/usr/bin
	install -d "$pkgdir"/etc
	install -d "$pkgdir"/usr/lib/systemd/system

	msg2 "coping files*******"

	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname "$pkgdir"/usr/bin/$pkgname
	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname.conf "$pkgdir"/etc/$pkgname.conf
	cp "$srcdir"/mpower_${pkgver}_x64/$pkgname.service "$pkgdir"/usr/lib/systemd/system/$pkgname.service

	msg2 "done coping files********"

}