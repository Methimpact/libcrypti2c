#! /usr/bin/guile -s
!#

(define l (list #x07 #x02 #x80 #x10 #x00))
(define a (list #x0B #x12 #x00 #x04 #x00 #xC0 #x00 #xAA #x00))

(use-modules (crypti2c configzone)
             (rnrs bytevectors)
             (crypti2c testing))

(test-begin "crc-test")

(test-equal (bytevector->hex-string (ci2c-crc16 (u8-list->bytevector a))) "83:0d")

(test-equal 128 (bytevector-length
                 (ci2c-xml-file->config-bv "data/atecc108_default.xml")))

(test-end "crc-test")
