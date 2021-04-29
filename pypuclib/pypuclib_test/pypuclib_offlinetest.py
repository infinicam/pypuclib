import unittest
import json
from PIL import Image
import numpy as np

import pypuclib
from pypuclib import Resolution, Decoder
from pypuclib import PUCException, WrapperException

class pypuclib_offlinetest(unittest.TestCase):
    def readJson(self, name):
        f = open(name, mode='rt', encoding='utf-8')
        dict = json.load(f)
        f.close()
        return dict

    def test_decoder(self):
        # Decoder quantization violation
        with self.assertRaises(WrapperException):
            dec = Decoder(list(range(10)))
        with self.assertRaises(WrapperException):
            dec = Decoder(list(range(80)))
        dec = Decoder()
        with self.assertRaises(WrapperException):
            dec.setQuantization([1,2,3])
        with self.assertRaises(WrapperException):
            dec.setQuantization(list(range(100)))

        # set quantization
        q = list(range(64))
        dec.setQuantization(q)
        self.assertEqual(dec.quantization(), q)
        q = list(range(-32, 32))
        dec.setQuantization(q)
        self.assertNotEqual(dec.quantization(), q) # should be clamped ushort
        q = list(range(65500, 65564))
        dec.setQuantization(q)
        self.assertNotEqual(dec.quantization(), q) # should be clamped ushort

    def prepare_data(self):
        self.dataname="data_w1246h1008_seq4658"
        self.dict = self.readJson(self.dataname+".json")
        self.decoder = Decoder(self.dict["quantization"])
        self.width = self.dict["width"]
        self.height = self.dict["height"]
        self.answerSeq=4658
        self.answerImg=np.load(self.dataname+"_answer"+".npy")
        self.compressedData=np.load(self.dataname+".npy")

    def test_extractSequenceNo(self):
        self.prepare_data()

        # correct
        seq = self.decoder.extractSequenceNo(self.compressedData, self.width, self.height)
        self.assertEqual(seq, self.answerSeq)

        # wrong resolution
        seq = self.decoder.extractSequenceNo(self.compressedData, self.width-8, self.height-8)
        self.assertNotEqual(seq, self.answerSeq)

    def test_numDecodeThread(self):
        self.prepare_data()

        self.decoder.setNumDecodeThread(1)
        self.assertEqual(1, self.decoder.numDecodeThread())

        self.decoder.setNumDecodeThread(8)
        self.assertEqual(8, self.decoder.numDecodeThread())

        with self.assertRaises(PUCException):
            self.decoder.setNumDecodeThread(33)
            array = self.decoder.decode(self.compressedData, Resolution(self.width, self.height))

    def test_decodeImage(self):
        self.prepare_data()

        for i in range(1,33):
            self.decoder.setNumDecodeThread(i)
            self.assertEqual(i, self.decoder.numDecodeThread())

            # decode full resolution
            img = self.decoder.decode(self.compressedData, Resolution(self.width, self.height))
            self.assertTrue(np.array_equal(img, self.answerImg))
            img = self.decoder.decode(self.compressedData, 0, 0, self.width, self.height)
            self.assertTrue(np.array_equal(img, self.answerImg))

            # decode roi
            x, y, w, h = 128, 64, 240, 132
            roi = self.decoder.decode(self.compressedData, x, y, w, h)
            self.assertTrue(np.array_equal(roi, self.answerImg[y:y+h, x:x+w]))

        # decode range violation
        with self.assertRaises(PUCException):
            roi = self.decoder.decode(self.compressedData, 1246, y, w, h)
        with self.assertRaises(PUCException):
            roi = self.decoder.decode(self.compressedData, x, 1200, w, h)
        with self.assertRaises(PUCException):
            roi = self.decoder.decode(self.compressedData, x, y, 1300, h)
        with self.assertRaises(PUCException):
            roi = self.decoder.decode(self.compressedData, x, y, w, 2000)
        with self.assertRaises(PUCException):
            roi = self.decoder.decode(self.compressedData, x+1, y, w, h)
        with self.assertRaises(PUCException):
            roi = self.decoder.decode(self.compressedData, x, y+1, w, h)

        # wrong resolution
        img = self.decoder.decode(self.compressedData, Resolution(self.width-8, self.height-8))
        self.assertFalse(np.array_equal(img, self.answerImg))

        # wrong quantization
        q = self.decoder.quantization()
        self.decoder.setQuantization(list(range(64)))
        img = self.decoder.decode(self.compressedData, Resolution(self.width-8, self.height-8))
        self.assertFalse(np.array_equal(img, self.answerImg))

if __name__ == '__main__':
    unittest.main()
