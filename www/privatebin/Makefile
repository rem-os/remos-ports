# Created by: Stefan Esser <se@FreeBSD.org>

PORTNAME=	privatebin
PORTVERSION=	1.3.5
CATEGORIES=	www security

MAINTAINER=	dvl@FreeBSD.org
COMMENT=	Simple end-to-end encrypting zero-knowledge paste-bin server

LICENSE=	ZLIB
LICENSE_FILE=	${WRKSRC}/LICENSE.md

USES=		php

NO_BUILD=	yes
NO_ARCH=	yes

USE_PHP=	gd hash json zlib
USE_GITHUB=	yes
GH_PROJECT=	PrivateBin

OPTIONS_DEFINE=	DOCS

post-patch:
	@${REINPLACE_CMD} -e 's:%%DATADBDIR%%:/var/db/${PORTNAME}:' \
		${WRKSRC}/index.php

do-install:
	@${MKDIR} ${STAGEDIR}${WWWDIR}
	@cd ${WRKSRC} && ${COPYTREE_SHARE} . ${STAGEDIR}${WWWDIR}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${MV} ${STAGEDIR}/${WWWDIR}/*.md ${STAGEDIR}/${DOCSDIR}
	@${MKDIR} ${STAGEDIR}/var/db/${PORTNAME}

.include <bsd.port.mk>
