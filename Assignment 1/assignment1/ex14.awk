#!/usr/bin/awk -f
BEGIN {
	{print "Hello"}
	exit
}
{
	# This occurs for each line input into awk
}
END {
	# This occurs at the end of a script after all lines
}

