// TODO: Include necessary libraries for serialization and deserialization

const WebSocket = require('ws');
const { stringify, parse } = require('nlohmann');

const JOIN_MESSAGE_TYPE = "JOIN";
const LEAVE_MESSAGE_TYPE = "LEAVE";

function send_join_message(username) {
  const join_message = { username };
  const serialized_message = stringify(join_message);
  // Send the serialized message to the signaling server
  ws.send(serialized_message);
}

function send_leave_message(username) {
  const leave_message = { username };
  const serialized_message = stringify(leave_message);
  // Send the serialized message to the signaling server
  ws.send(serialized_message);
}

const ws = new WebSocket('ws://107.131.124.5:8000');

ws.addEventListener('open', () => {
  const join_message = {
  type: JOIN_MESSAGE_TYPE,
  username: 'user'
  };
  const serialized_message = stringify(join_message);
  ws.send(serialized_message);
});

ws.addEventListener('message', (event) => {
  const message = parse(event.data);
  const message_type = message.type;

  if(message_type === JOIN_MESSAGE_TYPE) {
    handle_join_message(message);
  } else if (message_type === LEAVE_MESSAGE_TYPE) {
    handle_leave_message(message);
  }
});
//handle incoming messages from signaling server
function handle_join_message(message) {
  const { username } = message;
  console.log('${username} has joined the chat');
}
function handle_leave_message(message) {
  const { username } = message;
  console.log('${username} has left the chat');
}
