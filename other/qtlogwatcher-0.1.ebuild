# Copyright 1999-2013 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=5

inherit git-2

DESCRIPTION="A Logwatcher client using the Qt Framework"
HOMEPAGE="https://github.com/sperner/QtLogwatcher"
EGIT_PROJECT="QtLogwatcher"
EGIT_REPO_URI="https://github.com/sperner/QtLogwatcher/"

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~mips ~sparc ~x86 ~amd64"
#IUSE="ssl,sql"

DEPEND="dev-qt/qtcore
	dev-qt/qtgui
	dev-util/cmake
	dev-vcs/git"

src_compile() {
	qmake
	emake
}

src_install() {
	dobin QtLogwatcher
}
