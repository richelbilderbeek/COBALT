#################################
# $Id: Makefile.blast_macros.mk 499473 2016-04-26 14:40:22Z camacho $
# This file contains macro definitions for using libraries maintained by the
# BLAST TEAM
# Author:  Christiam Camacho (camacho@ncbi.nlm.nih.gov)
#################################


BLAST_FORMATTER_MINIMAL_LIBS = xblastformat align_format taxon1 blastdb_format \
    gene_info $(XFORMAT_LIBS) xalnmgr blastxml blastxml2 xcgi xhtml
# BLAST_FORMATTER_LIBS = $(BLAST_FORMATTER_MINIMAL_LIBS)
BLAST_FORMATTER_LIBS = $(BLAST_INPUT_LIBS)
BLAST_DB_DATA_LOADER_LIBS = ncbi_xloader_blastdb_rmt ncbi_xloader_blastdb
BLAST_INPUT_LIBS = blastinput \
    $(BLAST_DB_DATA_LOADER_LIBS) $(BLAST_FORMATTER_MINIMAL_LIBS)

# Libraries required to link against the internal BLAST SRA library
BLAST_SRA_LIBS=blast_sra $(SRAXF_LIBS) vxf $(SRA_LIBS)

# BLAST_FORMATTER_LIBS and BLAST_INPUT_LIBS need $BLAST_LIBS
BLAST_LIBS = xblast xalgoblastdbindex composition_adjustment \
		xalgodustmask xalgowinmask seqmasks_io seqdb blast_services xalnmgr \
		xobjutil $(OBJREAD_LIBS) xnetblastcli xnetblast blastdb scoremat tables
# BLAST additionally needs xconnect $(SOBJMGR_LIBS) or $(OBJMGR_LIBS)
