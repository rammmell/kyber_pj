from qiskit import QuantumCircuit, transpile
from qiskit.visualization import plot_histogram
from qiskit_ibm_runtime import QiskitRuntimeService, Sampler, Session

# IBM Quantum 계정 인증 (토큰은 보안상 직접 코드에 넣지 않는 것이 좋음)
service = QiskitRuntimeService(
    channel='ibm_quantum',
    instance='ibm-q/open/main',
    token='af8b791f1fe3aa104429c24eb1a334d5d550a3f5ee8a416d786585a08f0edfdde99b3af8fe6b029ec955863e5e515b5e4752d3ca5f431a541b69f4a1ace355a8'
)

backend = service.backend('ibm_sherbrooke') 

circuit = QuantumCircuit(5, 5)
for i in range(3):
    circuit.h(i)
circuit.barrier()
circuit.cx(0, 3)
circuit.cx(1, 3)
circuit.cx(2, 3)
circuit.ccx(0, 1, 4)
circuit.ccx(0, 2, 4)
circuit.ccx(1, 2, 4)
circuit.barrier()
circuit.measure([0, 1, 2, 3, 4], [0, 1, 2, 3, 4])
circuit.draw('mpl')

tp_result = transpile(circuit, backend)

with Session(backend=backend) as session:
    sampler = Sampler() 
    job = sampler.run([tp_result], shots=1024)
    result = job.result()
 

counts = result._pub_results[0].data.c.get_counts()
sorted_counts = dict(sorted(counts.items(), key=lambda x: x[0][:3]))
print(sorted_counts)
plot_histogram(sorted_counts)

