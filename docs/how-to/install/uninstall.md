# Installer Script Uninstallation (Linux)

To uninstall all ROCm packages and the kernel-mode driver the following commands
can be used.

::::{rubric} Uninstalling Single-Version Install
::::

```console shell
sudo amdgpu-install --uninstall
```

::::{rubric} Uninstalling a Specific ROCm Release
::::

```console shell
sudo amdgpu-install --uninstall --rocmrelease=<release-number>
```

::::{rubric} Uninstalling all ROCm Releases
::::

```console shell
sudo amdgpu-install --uninstall --rocmrelease=all
```
