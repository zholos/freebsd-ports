# $FreeBSD$

PORTNAME=	dedup
PORTVERSION=	0.4
CATEGORIES=	sysutils python
MASTER_SITES=	http://althenia.net/files/

MAINTAINER=	aaz@q-fu.com
COMMENT=	Delete duplicate files

LICENSE=	MIT

USE_PYTHON=	yes
NO_BUILD=	yes

PLIST_FILES=	bin/dedup man/man1/dedup.1.gz

post-patch:
	${REINPLACE_CMD} -e '1s|/.*|${PYTHON_CMD}|' ${WRKSRC}/dedup.py

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/dedup.py ${STAGEDIR}${PREFIX}/bin/dedup
	${INSTALL_MAN} ${WRKSRC}/dedup.1 ${STAGEDIR}${MAN1PREFIX}/man/man1

.include <bsd.port.mk>
