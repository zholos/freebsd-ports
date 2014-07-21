# $FreeBSD$

PORTNAME=	povray
DISTVERSION=	3.7.0.20140721
CATEGORIES=	graphics
PKGNAMESUFFIX=	37
DIST_SUBDIR=	${PORTNAME}${PKGNAMESUFFIX}

MAINTAINER=	bkoenig@alpha-tierchen.de
COMMENT=	Persistence of Vision Ray Tracer

LIB_DEPENDS=	libboost_thread.so:${PORTSDIR}/devel/boost-libs

USE_GITHUB=	yes
GH_ACCOUNT=	POV-Ray
GH_PROJECT=	povray
GH_COMMIT=	08c53d8
GH_TAGNAME=	${GH_COMMIT}

CONFLICTS_INSTALL=	povray37-3.7.0

OPTIONS_DEFINE=	X11 PNG JPEG TIFF OPENEXR STATIC IO EXAMPLES DOCS
OPTIONS_DEFAULT=PNG JPEG EXAMPLES DOCS
OPTIONS_SUB=	yes
IO_DESC=	Without I/O restrictions (security risk)
EXAMPLES_DESC=	Install example scenes
DOCS_DESC=	Install HTML documentation

USES=		gmake
USE_AUTOTOOLS=	autoconf:env automake:env
GNU_CONFIGURE=	yes

VERSION_BASE=	${PORTVERSION:C/([0-9]+\.[0-9]+).*/\1/}

DOCSDIR=	${PREFIX}/share/doc/${PORTNAME}-${VERSION_BASE}
EXAMPLESDIR=	${PREFIX}/share/examples/${PORTNAME}-${VERSION_BASE}
DATADIR=	${PREFIX}/share/${PORTNAME}-${VERSION_BASE}
ETCDIR=		${PREFIX}/etc/${PORTNAME}/${VERSION_BASE}

CPPFLAGS+=	-I${LOCALBASE}/include
LIBS+=		-L${LOCALBASE}/lib -lboost_system

CONFIGURE_ARGS=	COMPILED_BY=${MAINTAINER} \
		--program-transform-name='s/${PORTNAME}/${PORTNAME}${PKGNAMESUFFIX}/' \
		--disable-optimiz

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MX11}
USE_XORG=		xpm sm ice x11
USE_SDL=		sdl
.else
CONFIGURE_ARGS+=	--without-x
.endif

.if ${PORT_OPTIONS:MSTATIC}
CONFIGURE_ARGS+=--enable-static
.endif

.if ${PORT_OPTIONS:MIO}
CONFIGURE_ARGS+=--disable-io-restrictions
.endif

.if ${PORT_OPTIONS:MPNG}
.if ${PORT_OPTIONS:MSTATIC}
BUILD_DEPENDS+=	png>=1.4:${PORTSDIR}/graphics/png
.else
LIB_DEPENDS+=	libpng15.so:${PORTSDIR}/graphics/png
.endif
.else
CONFIGURE_ARGS+=--without-libpng
.endif

.if ${PORT_OPTIONS:MJPEG}
.if ${PORT_OPTIONS:MSTATIC}
BUILD_DEPENDS+=	jpeg>=6b:${PORTSDIR}/graphics/jpeg
.else
LIB_DEPENDS+=	libjpeg.so:${PORTSDIR}/graphics/jpeg
.endif
.else
CONFIGURE_ARGS+=--without-libjpeg
.endif

.if ${PORT_OPTIONS:MTIFF}
.if ${PORT_OPTIONS:MSTATIC}
BUILD_DEPENDS+=	tiff>=4:${PORTSDIR}/graphics/tiff
.else
LIB_DEPENDS+=	libtiff.so:${PORTSDIR}/graphics/tiff
.endif
.else
CONFIGURE_ARGS+=--without-libtiff
.endif

.if ${PORT_OPTIONS:MOPENEXR}
.if ${PORT_OPTIONS:MSTATIC}
BUILD_DEPENDS+=	OpenEXR>=1.6:${PORTSDIR}/graphics/OpenEXR
.else
LIB_DEPENDS+=	libIlmImf.so:${PORTSDIR}/graphics/OpenEXR
CPPFLAGS+=	-I${LOCALBASE}/include/OpenEXR
.endif
.else
CONFIGURE_ARGS+=--without-openexr
.endif

.if !${PORT_OPTIONS:MPNG} || !${PORT_OPTIONS:MJPEG} || !${PORT_OPTIONS:MTIFF}
CONFIGURE_ARGS+=NON_REDISTRIBUTABLE_BUILD=yes
.endif

.if ${ARCH} == "sparc64"
BROKEN=		Does not compile on sparc64: thread-local storage not supported
.endif

MAN1=		${PORTNAME}${PKGNAMESUFFIX}.1

PORTDOCS=	*
PORTEXAMPLES=	*

pre-configure:
	cd ${WRKSRC}/unix && ./prebuild.sh

pre-build:
.if ${PORT_OPTIONS:MSTATIC} && ${PORT_OPTIONS:MTIFF}
#	graphics/tiff adds dependencies on libjpeg and libjbig
	@${REINPLACE_CMD} -e 's,^\(LIBS = .*\)-ltiff\(.*\),\1-ltiff -ljpeg -ljbig -llzma\2,' ${WRKSRC}/unix/Makefile
.endif

post-install:
	${MV} ${STAGEDIR}${DATADIR}/scenes ${STAGEDIR}${EXAMPLESDIR}
.for i in povray.conf povray.ini
	${MV} ${STAGEDIR}${ETCDIR}/${i} ${STAGEDIR}${ETCDIR}/${i}.sample
.endfor

.include <bsd.port.mk>
