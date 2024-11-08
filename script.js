const addVehicleBtn = document.getElementById('addVehicle');
const addLightBtn = document.getElementById('addLight');
const decreaseEventBtn = document.getElementById('decreaseEvent');
const startSimulationBtn = document.getElementById('startSimulation');
const resetSimulationBtn = document.getElementById('resetSimulation');
const eventLog = document.getElementById('eventLog');
const timeDisplay = document.getElementById('timeDisplay');

// Simulated event data
let events = [];
let currentTime = 0;
let simulationInterval;

// Add vehicle event
addVehicleBtn.addEventListener('click', () => {
  const vehicle = prompt('Enter the vehicle name:');
  const timestamp = prompt('Enter the timestamp for the vehicle arrival:');
  events.push({
    type: 'vehicle_arrival',
    vehicle: vehicle,
    timestamp: parseInt(timestamp)
  });
  addEventToLog(`${timestamp}: ${vehicle} will arrive`);
});

// Add traffic light event
addLightBtn.addEventListener('click', () => {
  const lightColor = prompt('Enter the color for the traffic light change:');
  const timestamp = prompt('Enter the timestamp for the traffic light change:');
  events.push({
    type: 'traffic_light',
    lightColor: lightColor,
    timestamp: parseInt(timestamp)
  });
  addEventToLog(`${timestamp}: Traffic lights will change to ${lightColor}`);
});

// Decrease event time
decreaseEventBtn.addEventListener('click', () => {
  if (events.length > 0) {
    const eventToChange = prompt('Enter the timestamp of the event to decrease:');
    const newTime = prompt('Enter the new timestamp:');
    const eventIndex = events.findIndex((event) => event.timestamp === parseInt(eventToChange));
    if (eventIndex !== -1) {
      events[eventIndex].timestamp = parseInt(newTime);
      events.sort((a, b) => a.timestamp - b.timestamp);
      addEventToLog(`Event at ${eventToChange} changed to ${newTime}`);
    } else {
      alert('No event found with the given timestamp.');
    }
  } else {
    alert('No events to decrease.');
  }
});

// Start simulation
startSimulationBtn.addEventListener('click', () => {
  events.sort((a, b) => a.timestamp - b.timestamp);
  currentTime = 0;
  simulationInterval = setInterval(() => {
    timeDisplay.textContent = currentTime;
    events.forEach((event) => {
      if (event.timestamp === currentTime) {
        if (event.type === 'vehicle_arrival') {
          addEventToLog(`${event.timestamp}: ${event.vehicle} arrives`);
        } else if (event.type === 'traffic_light') {
          addEventToLog(`${event.timestamp}: Traffic lights change to ${event.lightColor}`);
        }
      }
    });
    currentTime++;
    if (currentTime > 100) {
      clearInterval(simulationInterval);
      addEventToLog('Simulation ended.');
    }
  }, 1000);
});

// Reset simulation
resetSimulationBtn.addEventListener('click', () => {
  clearInterval(simulationInterval);
  events = [];
  currentTime = 0;
  timeDisplay.textContent = '0';
  eventLog.innerHTML = '';
});

function addEventToLog(message) {
  const li = document.createElement('li');
  li.textContent = message;
  eventLog.appendChild(li);
}