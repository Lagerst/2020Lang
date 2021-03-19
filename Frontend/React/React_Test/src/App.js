import logo from './logo.svg';
import userLogo from './SVG Circles/ship.svg'
import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <img src={userLogo} className="User-logo" alt="logo" />
      </header>
    </div>
  );
}

export default App;
