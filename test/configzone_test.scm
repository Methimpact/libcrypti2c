#! /usr/bin/guile -s
!#

(use-modules (crypti2c configzone)
             (rnrs bytevectors)
             (crypti2c testing))

(define l (list #x07 #x02 #x80 #x10 #x00))
(define a (list #x0B #x12 #x00 #x04 #x00 #xC0 #x00 #xAA #x00))

(test-begin "crc-test")

(define ecc-data (ci2c-xml-file->config-bv
                  (string-concatenate
                   (list  (ci2c-get-data-dir) "/atecc108_default.xml"))))

(test-equal (bytevector->hex-string (ci2c-crc16 (u8-list->bytevector a))) "83:0d")

(test-equal 128 (bytevector-length ecc-data))

(test-end "crc-test")
