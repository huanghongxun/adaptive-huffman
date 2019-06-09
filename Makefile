all:
	@echo "make encoder or make decoder"

clean:
	rm -rf *.o *.out bin

.c.o:
	$(CXX) $(CXXFLAGS) -c $<

bin:
	mkdir -p bin

encoder: bin bin/encoder;

bin/encoder: encoder_test.o encoder.o huffman_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@

decoder: bin bin/decoder;

bin/decoder: decoder_test.o decoder.o huffman_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@

endecoder: bin bin/endecoder;

bin/endecoder: endecoder_test.o encoder.o decoder.o huffman_tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@