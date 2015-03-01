# Copyright 1999-2013 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=5

inherit eutils git-2

DESCRIPTION="A Logwatcher client using the Qt Framework"
HOMEPAGE="https://github.com/sperner/QtLogwatcher"
EGIT_PROJECT="QtLogwatcher"
EGIT_REPO_URI="https://github.com/sperner/QtLogwatcher/"

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~mips ~sparc ~x86 ~amd64"
IUSE="qt4"
#IUSE+="ssl,sql"

DEPEND="dev-qt/qtcore
	dev-qt/qtgui
	dev-util/cmake
	dev-vcs/git"

src_prepare() {
	if use qt4; then
		epatch "${FILESDIR}/qt4.patch"
	fi
}

src_compile() {
	qmake
	emake
}

src_install() {
	dobin QtLogwatcher

        insinto /etc
        doins config/qtlogwatcher.conf
	domenu config/qtlogwatcher.desktop

	doicon artwork/qtlogwatcher_active.png
	doicon artwork/qtlogwatcher_inactive.png

#	dodoc docs/{authors,changelog,install,license,news,readme}
	dodoc docs/{license,readme}
}
