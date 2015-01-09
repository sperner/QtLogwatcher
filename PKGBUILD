# Contributor: Jonathan Wiersma <archaur at jonw dot org>
pkgname=QtLogwatcher
pkgver=master
pkgrel=1
pkgdesc="Graphical logwatcher client using the qt framework"
arch=('i686' 'x86_64')
url="https://github.com/sperner/QtLogwatcher"
license=('GPL3')
depends=('qt4>=4.0')
makedepends=('gcc>=3' 'cmake' 'git')
optdepends=()
source=("git+https://github.com/sperner/QtLogwatcher")
md5sums=('SKIP')

build()
{
        cd "$srcdir/$pkgname"
	qmake || return 1
	make || return 1
}

package()
{
        cd "$srcdir/$pkgname"
        make DESTDIR="$pkgdir" install || return 1
}
