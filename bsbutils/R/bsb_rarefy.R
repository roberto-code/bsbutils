
bsb.rarefy <- function(mat, count.call){
	total.reads = colSums(mat)
	min.depth = as.integer( 0.9*min( total.reads ) )
	d = .Call( "rarefy", mat, min.depth, total.reads, count.call, PACKAGE = "bsbutils" )
    return(d)
}

