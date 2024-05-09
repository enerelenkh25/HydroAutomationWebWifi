let manualMode = false;
let sensorGraph = null;

const seedTable = {
  basil: { ph: "5.5 - 6.5", lightDuration: "14 - 16" },
  tomato: { ph: "5.5 - 6.5", lightDuration: "16 - 18" },
  lettuce: { ph: "5.5 - 6.0", lightDuration: "12 - 14" },
  beans: { ph: "6.0 - 7.0", lightDuration: "14 - 16" },
  beets: { ph: "6.0 - 6.5", lightDuration: "12 - 14" },
  celery: { ph: "6.0 - 7.0", lightDuration: "16 - 18" },
  chard: { ph: "6.0 - 6.8", lightDuration: "12 - 14" },
  cilantro: { ph: "6.5 - 7.5", lightDuration: "12 - 14" },
  cucumbers: { ph: "5.5 - 6.5", lightDuration: "16 - 18" },
  kale: { ph: "6.0 - 7.5", lightDuration: "14 - 16" },
  mint: { ph: "6.0 - 7.0", lightDuration: "14 - 16" },
  peppers: { ph: "5.5 - 6.0", lightDuration: "16 - 18" },
  radishes: { ph: "5.5 - 6.8", lightDuration: "14 - 16" },
  spinach: { ph: "6.0 - 7.0", lightDuration: "14 - 16" },
  springOnions: { ph: "6.0 - 7.0", lightDuration: "12 - 14" }
};

const phaseTable = {
  Germination: { temperature: "22 - 24", humidity: "80 - 90" },
  Seeding: { temperature: "18 - 22", humidity: "60 - 70" },
  "Vegetative Growth": { temperature: "24 - 28", humidity: "60 - 70" },
  Flowering: { temperature: "18 - 24", humidity: "50 - 60" },
  Pollination: { temperature: "20 - 25", humidity: "40 - 50" },
  Fruit: { temperature: "18 - 24", humidity: "40 - 50" }
};

function updateBoundaryConditions() {
  const selectedSeed = document.getElementById('seedSelect').value;
  const selectedPhase = document.getElementById('phaseSelect').value;

  const seedData = seedTable[selectedSeed];
  const phaseData = phaseTable[selectedPhase];

  document.getElementById('phRange').textContent = seedData.ph;
  document.getElementById('lightDuration').textContent = seedData.lightDuration;

  document.getElementById('temperatureRange').textContent = phaseData.temperature;
  document.getElementById('humidityRange').textContent = phaseData.humidity;
}

function showGraph(sensor) {
  // Destroy the previous graph if it exists
  if (sensorGraph) {
    sensorGraph.destroy();
  }

  const ctx = document.getElementById("sensorGraph").getContext("2d");

  sensorGraph = new Chart(ctx, {
    type: 'line',
    data: {
      labels: Array.from({ length: 10 }, (_, i) => i + 1),
      datasets: [{
        label: sensor,
        data: [], // Placeholder for real sensor data
        borderColor: 'blue',
        borderWidth: 2
      }]
    },
    options: {
      responsive: true,
      scales: {
        x: { title: { display: true, text: 'Time' } },
        y: { title: { display: true, text: sensor } }
      }
    }
  });
}

function toggleComponent(component) {
  if (!manualMode) {
    alert('Cannot change in Auto mode. Please switch to Manual mode.');
    return;
  }

  const statusElement = document.getElementById(`status${component.charAt(0).toUpperCase() + component.slice(1).toLowerCase()}`);
  const buttonElement = document.getElementById(`toggle${component.charAt(0).toUpperCase() + component.slice(1).toLowerCase()}`);

  const currentStatus = statusElement.textContent === 'ON';
  const newState = currentStatus ? 'OFF' : 'ON';

  statusElement.textContent = newState;
  statusElement.classList.toggle('off', !currentStatus);
  statusElement.classList.toggle('on', currentStatus);
  buttonElement.classList.toggle('on', !currentStatus);
  buttonElement.classList.toggle('off', currentStatus);
  buttonElement.textContent = `Turn ${currentStatus ? 'OFF' : 'ON'}`;

  alert(`YOU ARE TRYING TO TURN ${newState} ${component}.`);
}

function changeControlMode() {
  const controlMode = document.getElementById('controlMode').value;
  manualMode = (controlMode === 'manual');
  console.log(`Control Mode changed to: ${controlMode}`);

  const buttons = document.querySelectorAll('.toggle-btn');
  buttons.forEach(button => {
    button.disabled = !manualMode;
    button.classList.toggle('manual-mode', manualMode);
  });
}

function changeSeed() {
  console.log(`Seed changed to: ${document.getElementById('seedSelect').value}`);
  updateBoundaryConditions();
}

function changePhase() {
  console.log(`Phase changed to: ${document.getElementById('phaseSelect').value}`);
  updateBoundaryConditions();
}
