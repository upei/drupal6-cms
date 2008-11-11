SimpleXML Parser
================

Provides a more generic XML parser than the SimplePie parser.

Please transform any XML in to the following format so the parser can read it.

===============================================================================
<feed title="[some feed title]" description="[some feed description]">
	<node id="the node id" title="[some node title]" description="[some node description]">
		<data>
			<!-- any tags can be inserted here -->
		</data>
	</node>
	<node id="the second node id" title="some title" description="some description">
		<data>
			<!-- any node data -->
		</data>
	</node>
	<!-- nodes -->
</feed>
===============================================================================

The format of data inside every node's data should be consistent.
 