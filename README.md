# Linux Installation Documentation

## Building our documentation

For a quick-start build, use the following code. For more options and detail, refer to
[Building documentation](./contribute/building.md).

```bash
cd docs

pip3 install -r sphinx/requirements.txt

python3 -m sphinx -T -E -b html -d _build/doctrees -D language=en . _build/html
```
