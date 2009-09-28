<?xml version="1.0"?>

<!--
  To regenerate the FAQ:
    xsltproc -''-nodtdattr faq-web.xsl faq.xhtml >| www/faq.html
-->

<!DOCTYPE stylesheet [
<!ENTITY nl '<xsl:text xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
</xsl:text>'>
]>

<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:h="http://www.w3.org/1999/xhtml"
                xmlns="http://www.w3.org/1999/xhtml"
                exclude-result-prefixes="h">

<xsl:output method="xml"
            encoding="iso-8859-1"
            doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN"
            doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"
            indent="no"/>

<xsl:template match="processing-instruction('questions')">
  <ol>&nl;
    <xsl:for-each select="following-sibling::h:dl[@class = 'faq']/h:dt">
      <li><a href="#{@id}"><xsl:apply-templates select="node()"/></a></li>&nl;
    </xsl:for-each>
  </ol>
</xsl:template>

<xsl:template match="h:dt">
  <xsl:copy>
    <xsl:apply-templates select="@*"/>
    <xsl:value-of select="concat(1 + count(preceding-sibling::h:dt), '. ')"/>
    <xsl:apply-templates select="node()"/>
  </xsl:copy>
</xsl:template>

<xsl:template match="node()|@*">
  <xsl:copy>
    <xsl:apply-templates select="node()|@*"/>
  </xsl:copy>
</xsl:template>

</xsl:stylesheet>
