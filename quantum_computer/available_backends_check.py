from qiskit_ibm_runtime import QiskitRuntimeService

service = QiskitRuntimeService(
    channel='ibm_quantum',
    instance='ibm-q/open/main',
    token='af8b791f1fe3aa104429c24eb1a334d5d550a3f5ee8a416d786585a08f0edfdde99b3af8fe6b029ec955863e5e515b5e4752d3ca5f431a541b69f4a1ace355a8'
)
# Print available backends
available_backends = service.backends()
print("Available Backends:", [backend.name for backend in available_backends])