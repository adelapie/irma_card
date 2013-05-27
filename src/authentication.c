/**
 * authentication.c
 *
 * This file is part of IRMAcard.
 *
 * IRMAcard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * IRMAcard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IRMAcard. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) May 2012 - 2013.
 *   Pim Vullers <pim@cs.ru.nl>, Radboud University Nijmegen.
 */

#include "authentication.h"

#include "APDU.h"
#include "ASN1.h"
#include "debug.h"
#include "memory.h"
#include "random.h"
#include "utils.h"
#include "SHA.h"
#include "RSA.h"

unsigned char *authentication_verifyCertificate(RSA_public_key *key, unsigned char *cert) {
  TLV tlv;
  unsigned char *body, *signature;
  int body_bytes, signature_bytes;
  unsigned int offset = 0;

  ASN1_decode_tlv(&tlv, cert, &offset);
  if (tlv.tag != 0x7F21) {
	  APDU_ReturnSW(SW_WRONG_DATA);
  }
  body = tlv.value;
  offset = tlv.value - cert;

  ASN1_decode_tlv(&tlv, cert, &offset);
  if (tlv.tag != 0x7F4E) {
	  APDU_ReturnSW(SW_WRONG_DATA);
  }
  body_bytes = cert + offset - body;

  ASN1_decode_tlv(&tlv, cert, &offset);
  if (tlv.tag != 0x5F37) {
	  APDU_ReturnSW(SW_WRONG_DATA);
  }
  signature_bytes = tlv.length;
  signature = tlv.value;

  if (RSA_PSS_verify(key, body_bytes, body, signature_bytes, signature) < 0) {
    APDU_ReturnSW(SW_SECURITY_STATUS_NOT_SATISFIED);
  }

  return body;
}

void authentication_parseCertificate(unsigned char *cert) {
  unsigned int offset = 0;

}

void authentication_generateChallenge(RSA_public_key *key, unsigned char *nonce, unsigned char *challenge) {
  RandomBytes(nonce, AUTH_CHALLENGE_BYTES);
  RSA_OAEP_encrypt(challenge, key, AUTH_CHALLENGE_BYTES, nonce, 0, NULL);
}

void authentication_authenticateTerminal(unsigned char *response, unsigned char *nonce) {
  if (NotEqual(AUTH_CHALLENGE_BYTES, response, nonce)) {
    APDU_ReturnSW(SW_WRONG_DATA);
  }
}
