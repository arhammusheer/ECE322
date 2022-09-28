BEGIN {
	{
		print $1
	}
	exit
}
{
}
END {
	print NR
}

