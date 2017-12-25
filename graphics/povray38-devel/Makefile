# $FreeBSD$

PORTNAME=	povray
DISTVERSIONPREFIX=	v
DISTVERSION=	3.8.0-alpha.9436902
CATEGORIES=	graphics
PKGNAMESUFFIX=	38
DIST_SUBDIR=	${PORTNAME}${PKGNAMESUFFIX}

MAINTAINER=	bkoenig@alpha-tierchen.de
COMMENT=	Persistence of Vision Ray Tracer

LIB_DEPENDS=	libboost_thread.so:devel/boost-libs

BROKEN_powerpc64=	Does not build: c++: Internal error: Killed (program cc1plus)

USE_GITHUB=	yes
GH_ACCOUNT=	POV-Ray

OPTIONS_DEFINE=	X11 PNG JPEG TIFF OPENEXR STATIC IO EXAMPLES DOCS
OPTIONS_DEFAULT=PNG JPEG
OPTIONS_SUB=	yes
IO_DESC=	Without I/O restrictions (security risk)
EXAMPLES_DESC=	Install example scenes
DOCS_DESC=	Install HTML documentation

USES=		gmake autoreconf:build
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
BUILD_DEPENDS+=	png>=1.4:graphics/png
.else
LIB_DEPENDS+=	libpng.so:graphics/png
.endif
.else
CONFIGURE_ARGS+=--without-libpng
.endif

.if ${PORT_OPTIONS:MJPEG}
.if ${PORT_OPTIONS:MSTATIC}
USES+=		jpeg:build
.else
USES+=		jpeg
.endif
.else
CONFIGURE_ARGS+=--without-libjpeg
.endif

.if ${PORT_OPTIONS:MTIFF}
.if ${PORT_OPTIONS:MSTATIC}
BUILD_DEPENDS+=	tiff>=4:graphics/tiff
.else
LIB_DEPENDS+=	libtiff.so:graphics/tiff
.endif
.else
CONFIGURE_ARGS+=--without-libtiff
.endif

.if ${PORT_OPTIONS:MOPENEXR}
.if ${PORT_OPTIONS:MSTATIC}
BUILD_DEPENDS+=	OpenEXR>=1.6:graphics/OpenEXR
.else
LIB_DEPENDS+=	libIlmImf.so:graphics/OpenEXR
CPPFLAGS+=	-I${LOCALBASE}/include/OpenEXR
.endif
.else
CONFIGURE_ARGS+=--without-openexr
.endif

.if !${PORT_OPTIONS:MPNG} || !${PORT_OPTIONS:MJPEG} || !${PORT_OPTIONS:MTIFF}
CONFIGURE_ARGS+=NON_REDISTRIBUTABLE_BUILD=yes
.endif

PORTDOCS=	*
PORTEXAMPLES=	*

post-patch:
	${REINPLACE_CMD} -e 's|@@EXAMPLESDIR@@|${EXAMPLESDIR}|' \
		-e 's|@@ETCDIR@@|${ETCDIR}|' \
		${WRKSRC}/unix/povray.conf

pre-configure:
	cd ${WRKSRC}/unix && ./prebuild.sh

pre-build:
.if ${PORT_OPTIONS:MSTATIC} && ${PORT_OPTIONS:MTIFF}
#	graphics/tiff adds dependencies on libjpeg, libjbig and liblzma
	@${REINPLACE_CMD} -e 's,^\(LIBS = .*\)-ltiff\(.*\),\1-ltiff -ljpeg -ljbig -llzma\2,' ${WRKSRC}/unix/Makefile
.endif

post-install:
	${MV} ${STAGEDIR}${DATADIR}/scenes ${STAGEDIR}${EXAMPLESDIR}
.for i in povray.conf povray.ini
	${MV} ${STAGEDIR}${ETCDIR}/${i} ${STAGEDIR}${ETCDIR}/${i}.sample
.endfor

.include <bsd.port.mk>
