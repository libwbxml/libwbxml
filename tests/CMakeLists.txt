
ENABLE_TESTING()
CONFIGURE_FILE( "launchTests.sh" "${CMAKE_CURRENT_BINARY_DIR}/launchTests.sh")
CONFIGURE_FILE( "normalize_xml.pl" "${CMAKE_CURRENT_BINARY_DIR}/normalize_xml.pl" @ONLY)
SET( activesync_tests 12 )
SET( airsync_tests 4 )
SET( ddf_tests 2 )
# 2009-Jan-19 bellmich
# All DRMREL 1.0 tests are switched off.
# The background is the extremely bad specification.
# DRMREL 1.0 hardcodes the XML namespace translation.
# I never saw such a broken XML design before.
#
#SET( drmrel_tests  3 )
SET( emn_tests    17 )
SET( ota_tests     3 )
SET( prov_tests    8 )
SET( si_tests     25 )
SET( sl_tests     13 )
SET( syncml_tests 14 )
SET( wv_tests    116 )
SET( conml_tests   2 )
FOREACH( TESTDIR activesync airsync conml ddf emn ota prov si sl syncml wv )
	FOREACH( ITEM RANGE 1 ${${TESTDIR}_tests} )
		ADD_TEST( "tools_document_${TESTDIR}_${ITEM}" launchTests.sh "${CMAKE_CURRENT_SOURCE_DIR}" "${TESTDIR}" ${ITEM} )
	ENDFOREACH( ITEM RANGE 1 ${${TESTDIR}_tests} )
ENDFOREACH( TESTDIR activesync airsync conml ddf emn ota prov si sl syncml wv )

