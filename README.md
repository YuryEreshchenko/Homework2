# Interactive Toy

A simple Arduino interactive pet toy that responds to touch and displays its mood through RGB LED colors.

## Description

This interactive toy uses an RGB LED to show its emotional state. The toy becomes happier when you interact with it by pressing a button (petting), and becomes sad when ignored for too long. If the toy gets extremely unhappy, it will flash to get your attention.

## How It Works

### Mood System

The toy has a mood level ranging from 0 to 20 and will showcase its state in the Serial Monitor

- **0-5**: Very bad mood 
- **6-10**: Bad mood 
- **11-15**: Neutral mood 
- **16-20**: Happy mood

### Interactions

- **Petting**: Press the button to increase the mood level (+1 per press)
- **Ignoring**: After 5 seconds of no interaction, the mood decreases by 1 every second
- **Maximum happiness**: Mood caps at 20
- **Minimum mood**: Bottoms out at 0 (flashing alert mode)

## Author

Yury Ereshchenko (114012010)

Date: October 29, 2025