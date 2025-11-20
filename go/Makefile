.PHONY: all test coverage clean run

all: test

test:
	go test ./...

coverage:
	go test -coverprofile=coverage.out ./...
	go tool cover -html=coverage.out -o coverage.html
	@echo "Coverage report generated in coverage.html"

run:
	go run cmd/main.go

clean:
	rm -f coverage.out coverage.html
